vim.api.nvim_create_user_command("CPCopy",
  function()
    local bufnr = vim.api.nvim_get_current_buf()
    local lines = vim.api.nvim_buf_get_lines(bufnr, 0, -1, false)
    vim.fn.setreg("+", lines)
  end,
  {
    desc = "Copy buffer contents to system clipboard"
  }
)

vim.api.nvim_create_user_command("CPPaste",
  function()
    local bufnr = vim.api.nvim_get_current_buf()
    local paste_content = vim.fn.getreg("+")
    vim.api.nvim_buf_set_lines(bufnr, 0, -1, false, {})
    vim.api.nvim_paste(paste_content, true, -1)
    vim.cmd("write")
  end,
  {
    desc = "Replace buffer with clipboard content and save"
  }
)
